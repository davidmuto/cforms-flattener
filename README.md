# cforms-flattener

A library that will "flatten" out cforms entries into a single record per submission an export to a CSV File

## Usage

    cforms-flattener <config_file> <cform_id> <output_file>

## Sample Usage

Make a configuration file containing the following lines

    tcp://HOST:PORT
    USERNAME
    PASSWORD
    CATALOG
    TABLE_PREFIX

For example assume we create a file called config

    tcp://localhost:3306
    root
    myRootPassword
    wp_cforms_demo
    wp_

To run the application, execute the following command

    cforms-flattener config myformid output.csv