import os
import re

# Main entry point
def run(name, template_file_path):
    print("name: %s" % name)
    print("path: %s" % template_file_path)
    # Get the raw template text
    template = get_template(template_file_path)
    # Fill the template with the given name
    filled_template = fill_template(template, name)    
    # Generate the file name
    output_file_name = generate_file_name(name, template_file_path)
    print("out: %s" % output_file_name)
    # Generate the file
    generate_file(output_file_name, filled_template)

# Get the raw template data from the templatefile
def get_template(file_path):
    with open(file_path, "r") as file:
        return file.read()

def fill_template(template, name):
    # Generate an uppercase name with underscores
    name_upper_und = get_name_uppercase_underscore(name)
    # Fill template with the new name
    filled = template.replace("NAME_AS_IS", name)
    return filled.replace("NAME_CAP_UND", name_upper_und)

# Convert the name from CamelCase to upper-snake case
def get_name_uppercase_underscore(name):
    # Convert camelcase to underscores, stage 1
    s1 = re.sub("(.)([A-Z][a-z]+)", r"\1_\2", name)
    # Replace generated double underscores
    s2 = re.sub("(__)", "_", s1)
    # Finish the conversion and make it uppercase
    return re.sub("([a-z0-9])([A-Z])", r"\1_\2", s2).upper()

# Generate a file name using the extension of the template
def generate_file_name(name, template_file_path):
    root, extension = os.path.splitext(template_file_path)
    return name + extension

# Write the raw generated data to the target file
def generate_file(file_path, filled_template):
    with open(file_path, "w") as file:
        file.write(filled_template)
