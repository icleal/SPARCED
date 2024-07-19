#!/usr/bin/env python     
# -*- coding: utf-8 -*-
# ----------------------------------------------------------------------------#
import libsbml
import importlib.util
import numpy as np
import pandas as pd
import os
import sys
import yaml

class Utils:
    """A class for storing helper functions for the benchmarks
    """
    @staticmethod
    def _results_size_checker(species_data, time_trajectories):
        """Check the size of the results dictionary
        input:
            species_data: np.array - the species data
            time_trajectories: np.array - the time trajectories
        
        output:
            returns the species and time trajectories, if larger than 2.4gb; 
            trims the results dictionary to every 1/4th of the data
        """
        
        size = sys.getsizeof(species_data)

        threshold_bytes = 2.4 * 1024**3

        while size > threshold_bytes:
            # cut every ith element until the size is less than the threshold
            species_data = species_data[::2]
            time_trajectories = time_trajectories[::2]

            size = sys.getsizeof(species_data)
        print(f"Size of results dictionary: {size} bytes")
        return species_data, time_trajectories


    @staticmethod
    def _tasks_this_round(size, total_jobs, round_number):
        """Calculate the number of tasks for the current round
        input:
            size: int - the total number of processes assigned
            total_jobs: int - the total number of tasks
        
        output:
            returns the number of tasks for the current round
        """
        number_of_rounds = Utils._number_of_rounds(total_jobs, size)

        tasks_per_round = size
        remainder = total_jobs % size

        # This accounts for pythonic indexing starting at 0
        round_number += 1

        if round_number < number_of_rounds:
            tasks_this_round = tasks_per_round
        elif round_number == number_of_rounds and remainder != 0:
            tasks_this_round = remainder
        elif round_number == number_of_rounds and remainder == 0:
            tasks_this_round = tasks_per_round
        else:
            #provide an error and message exit
            raise ValueError("Round number exceeds the number of rounds")

        return tasks_this_round
    

    @staticmethod
    def _condition_cell_id(rank_task, conditions_df, measurement_df):
        """
        Extract the condition for the task from the filtered_conditions
        output:
            returns the condition for the task
        """
        filtered_conditions = Utils._filter_conditions(conditions_df, measurement_df)
        
        cell = rank_task.split('+')[1]

        condition_id = rank_task.split('+')[0]
        
        condition = ([
            condition for condition in filtered_conditions if 
            condition['conditionId'] == condition_id][0]) 
    
        return condition, cell, condition_id

    @staticmethod
    def _results_dictionary(conditions_df, measurement_df):
        """Create an empty dictionary for storing results
        input:
            filtered_conditions: pd.DataFrame - filtered conditions dataframe
        
        output:
            returns the empty results dictionary, ready to be filled
        """

        filtered_conditions = Utils._filter_conditions(conditions_df, measurement_df)

        results = {}

        for condition in filtered_conditions:
            condition_id = condition['conditionId']
            results[condition_id] = {}
            num_cells = condition['num_cells'] if 'num_cells' in condition else 1
            for cell in range(num_cells):
                results[condition_id][f'cell {cell}'] = {}
        return results


    @staticmethod
    def _number_of_rounds(total_jobs, size):
        """Calculate the number of rounds
        input:
            total_jobs: int - the total number of tasks
            size: int - the total number of processes assigned
        
        output:_number_of_rounds
            returns the number of rounds
        """
        rounds_to_complete = total_jobs // size

        remainder = total_jobs % size

        if remainder > 0:
        
            rounds_to_complete += 1
        
        return rounds_to_complete


    @staticmethod
    def _total_tasks(conditions_df, measurement_df):
        """Calculate the total number of tasks
        input:
            conditions_df: pd.DataFrame - conditions dataframe
        
        output:
            returns the total number of tasks
        """

        filtered_conditions = Utils._filter_conditions(conditions_df, measurement_df)

        list_of_jobs = []

        for condition in filtered_conditions: 
            if 'num_cells' not in condition:
                condition_cell = f"{condition['conditionId']}+0"
                list_of_jobs.append(condition_cell)
            else:
                for cell in range(condition['num_cells']):
                    condition_cell = f"{condition['conditionId']}+{cell}"
                    list_of_jobs.append(condition_cell)

        return list_of_jobs


    @staticmethod
    def _filter_conditions(conditions_df, measurement_df):
        """Filter the conditions dataframe to only include unique conditions
        input:
            conditions_df: pd.DataFrame - conditions dataframe
        
        output:
            returns the unique conditions dataframe
        """
        filtered_conditions = ([
            condition for index, condition in conditions_df.iterrows()
            if 'preequilibrationConditionId' not in measurement_df.columns
            or condition['conditionId'] not in
            measurement_df['preequilibrationConditionId'].values
            ])
        
        return filtered_conditions


    @staticmethod
    def _assign_tasks(rank, total_jobs,size):
        """Assign tasks to ranks based on the number of jobs and the number of 
            ranks
        input:
            rank: int - the rank of the current process
            total_jobs: int - the total number of tasks
            size: int - the total number of processes assigned
        output:
            returns the start and end cell for each rank
        """
        jobs_per_rank = total_jobs // int(size)
        remainder = total_jobs % int(size)
        
        if rank < remainder:
            rank_i_jobs = jobs_per_rank + 1
            start_cell = rank * rank_i_jobs
        else:
            rank_i_jobs = jobs_per_rank
            start_cell = rank * jobs_per_rank + remainder
            
        return start_cell, start_cell + rank_i_jobs


    @staticmethod # Not even sure if this one works
    def _set_compartmental_volume(model: libsbml.Model, compartment: str, 
                                  compartment_volume: int):
        """This function sets the volume of a compartment within the SBML model.
        input:
            model: libsbml.Model - the SBML model
            compartment: str - the compartment to set
            compartment_volume: int - the volume to set the compartment to
        output:
            model: libsbml.Model - the updated SBML model
        """
        # Get the list of compartments
        compartment_ids = list(model.getCompartmentIds())

        # assign the compartment volume
        model.setCompartmentVolumeById(compartment, compartment_volume)

        return model
    

    @staticmethod
    def _set_parameter_value(model: libsbml.Model, parameter: str, 
                             parameter_value: int):
        """This function sets the value of a parameter within the SBML model.
        input:
            model: libsbml.Model - the SBML model
            parameter: str - the parameter to set
            parameter_value: int - the value to set the parameter to
        output:
            model: libsbml.Model - the updated SBML model
        """
        # Get the list of parameters
        parameter_ids = list(model.getParameterIds())

        try:# assign the parameter value
            model.setParameterById(parameter, parameter_value)
        except RuntimeError:
            model.setFixedParameterById(parameter, parameter_value)

        return model


    # Set this to static method to avoid the need to pass self
    @staticmethod
    def _set_species_value(model: libsbml.Model, species: str, 
                            species_value: int):
        """Thiss function sets the initial value of a species or list of species
        within the sbml model.
        input:
            model: libsbml.Model - the SBML model
            species_value: int - the value to set the species to
            
            output:
                model: libsbml.Model - the updated SBML model"""
        
        # Get the list of species
        species_ids = list(model.getStateIds())

        # Get the initial values
        species_initializations = np.array(model.getInitialStates())
        
        # Set the initial values
        index = species_ids.index(species)

        species_initializations[index] = species_value

        model.setInitialStates(species_initializations)
        
        return model


    @staticmethod
    def _assign_sbml_path(model_path: str):

        # Construct paths to SBML files in the specified directory
        sbml_files = [os.path.join(model_path, filename) for filename in os.listdir(model_path) if filename.endswith('.xml')][0]

        # return the sbml file path
        return sbml_files


    @staticmethod
    def _import_module_from_path(module_path: str):
        # Add the directory containing the module to sys.path
        module_dir = os.path.dirname(module_path)
        sys.path.append(module_dir)

        # Extract the module name from the path
        module_name = os.path.splitext(os.path.basename(module_path))[0]

        # Import the module dynamically
        spec = importlib.util.spec_from_file_location(module_name, module_path)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)

        # Remove the directory from sys.path to avoid affecting other imports
        sys.path.remove(module_dir)

        return module
    

    @staticmethod
    def _add_amici_path(model_path: str):
        """This function finds the AMICI model from the path
        input:
            model_path: str - the path to the model
        output:
            amici_module_path: str - the path to the AMICI module
        """
        # Get the directory contents
        try:
            directory_contents = os.listdir(model_path)
        except FileNotFoundError:
            raise ValueError(f"Model path '{model_path}' does not exist.")

        # Ignore any potential directories labeled 'results'
        directory_contents = [d for d in directory_contents if d != 'results']

        # Find the AMICI module via its setup.py file
        amici_module_path = None
        for directory in directory_contents:
            dir_path = os.path.join(model_path, directory)
            if os.path.isdir(dir_path):
                setup_path = os.path.join(dir_path, 'setup.py')
                if os.path.isfile(setup_path):
                    try:
                        with open(setup_path, 'r') as setup_file:
                            first_line = setup_file.readline().strip()
                            if 'AMICI model package setup' in first_line:
                                amici_module_path = dir_path
                                sys.path.append(amici_module_path)
                                break
                    except IOError as e:
                        print(f"Error reading setup file: {e}")

        if amici_module_path is None:
            raise ValueError("No valid AMICI module found in the provided path.")

        return amici_module_path

    @staticmethod
    def _swig_interface_path(model_path: str):
        """This function finds the SWIG python interface from the path
        input:
            model_path: str - the path to the model
        output:
            swig_interface_path: str - the path to the SWIG python interface
        """
        amici_module_path = Utils._add_amici_path(model_path)

        # Get the directory contents
        try:
            amici_contents = os.listdir(amici_module_path)
        except FileNotFoundError:
            raise ValueError(f"AMICI module path '{amici_module_path}' does not exist.")

        directories = [item for item in amici_contents 
                       if os.path.isdir(os.path.join(amici_module_path, item))]

        # Iterate over the directories to find the SWIG interface file
        swig_interface_path = None
        for directory in directories:
            directory_path = os.path.join(amici_module_path, directory)
            try:
                directory_contents = os.listdir(directory_path)
            except FileNotFoundError:
                continue
            
            for item in directory_contents:
                if item == directory + '.py':
                    swig_interface_path = os.path.join(directory_path, item)
                    break

            if swig_interface_path:
                break

        if swig_interface_path is None:
            raise ValueError("No SWIG interface file found in the AMICI module directories.")

        return swig_interface_path


    @staticmethod
    def _extract_simulation_files(model_path: str):
        """This function extracts the simulation files from the model path
        Input:
            model_path: str - the path to the model
        Output:
            simulation_files: list - the list of simulation files
        
        """
        # Filters for the data folder and config.yaml file within
        try:
            directory_contents = os.listdir(model_path)

            data_dir = [d for d in directory_contents if d == 'data'][0]
            
            data_path = os.path.join(model_path, data_dir)

            config_file = [f for f in os.listdir(data_path) if f == 'config.yaml'][0]

            config_path = os.path.join(data_path, config_file)

        except FileNotFoundError:

            raise ValueError(f"No config.yaml file found in the data directory of {model_path}; check model path.")
            
        with open(config_path, 'r') as f:
            config = yaml.safe_load(f)

        try:
            sim_file_dir = os.path.join(data_path, config['simulation']['root'])

            genereg = config['simulation']['genereg']

            GeneReg = os.path.join(sim_file_dir, genereg)

            omicsdata = config['simulation']['omics']

            OmicsData = os.path.join(sim_file_dir, omicsdata)

        except KeyError:
            raise KeyError(f"Simulation files not found in {data_dir}")
        
        return GeneReg, OmicsData



    @staticmethod
    def _set_transcription_values(model_path: str, gene: str, value: int) -> None:
        """This function sets the value of a parameter within the SBML model.
            input:
                model_path:  model_path: str - the path to the model
                gene: str - the gene to knockout
                value: int - the value to set the gene to
            output:
                model: libsbml.Model - the updated SBML model
        """

        gene_reg, omics_data = Utils._extract_simulation_files(model_path)
        
        # Read the omics_data file into a DataFrame
        omics_data_df = pd.read_csv(omics_data, sep='\t')

        prior_values = {}

        if gene in omics_data_df['gene'].values:
            # Extract prior values
            prior_values['kTCleak'] = omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCleak'].values[0]
            prior_values['kTCmaxs'] = omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCmaxs'].values[0]
            prior_values['kTCd'] = omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCd'].values[0]

            # Update values
            omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCleak'] = value
            omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCmaxs'] = value
            omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCd'] = value

        # Write the updated DataFrame back to the file
        omics_data_df.to_csv(omics_data, sep='\t', index=False)

        return prior_values


    @staticmethod
    def _reset_transcription_values(prior_values: dict, model_path: str) -> None:
        """This function resets the values of the transcription factors
        input:
            prior_values: dict - the values to reset
            model_path: str - the path to the model
        output:
            None
        """

        gene_reg, omics_data = Utils._extract_simulation_files(model_path)
        
        # Read the omics_data file into a DataFrame
        omics_data_df = pd.read_csv(omics_data, sep='\t')

        for gene, values in prior_values.items():
            if values is not None and gene in omics_data_df['gene'].values:
                omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCleak'] = values['kTCleak']
                omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCmaxs'] = values['kTCmaxs']
                omics_data_df.loc[omics_data_df['gene'] == gene, 'kTCd'] = values['kTCd']

        # Write the updated DataFrame back to the file
        omics_data_df.to_csv(omics_data, sep='\t', index=False)
