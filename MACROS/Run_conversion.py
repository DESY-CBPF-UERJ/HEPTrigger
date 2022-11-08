import os


def change_template(name_folder_samples,output_file,year):
    # Read in the file
    with open('Conversion_TEMPLATE.C', 'r') as file :
        filedata = file.read()

    # Replace the target string
    filedata = filedata.replace('@-@', name_folder_samples)
    filedata = filedata.replace('@--@', year)
    filedata = filedata.replace('@---@', output_file)

    # Write the file out again
    with open('Conversion_sample'+name_folder_samples+".C", 'w') as file:
        file.write(filedata)
        
    os.system("root -q Conversion_sample"+name_folder_samples+".C")
    os.system("rm Conversion_sample"+name_folder_samples+".C")
