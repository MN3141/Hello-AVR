#Used Python version Python 3.9.13
'''
This script shall be used to generate projects
Available extensions:.c and .s(assembly)
If none of the above extensions is provided,
the script shall default to .c
'''

import sys
import os

DEFAULT_TYPE='c'
ASSEMBLY_DEFAULT_CODE='''start:
    inc r16
    rjmp start'''
C_DEFAULT_CODE='''#include <avr/io.h>

int main(void)
{
 while (1) 
    {
    }
}
'''

project_name='fooname'
project_type='footype'
project_dir_path='foodir'
project_default_code='foocode'
project_name=sys.argv[1]
project_type=sys.argv[2]
root=os.getcwd()

if os.name =='nt':
    separator_character='\\'
    #Windows OS
elif os.name =='posix':
    separator_character='/'
    #POSIX based OS

if (sys.argv[2] !='c') and (sys.argv[2] !='s'): #checking if it is C or assembly
    project_type=DEFAULT_TYPE

if project_type =='c':
    project_dir_path=root+separator_character+'c'+separator_character+project_name
    project_default_code=C_DEFAULT_CODE
else:
    project_dir_path=root+separator_character+'asamblare'+separator_character+project_name
    project_default_code=ASSEMBLY_DEFAULT_CODE

if not os.path.exists(project_dir_path): #checking if the project has been created already
    os.mkdir(project_dir_path)
    with open(root+separator_character+'template'+separator_character+'Makefile',"r") as f:
        file_buffer=f.read()
        f.close()
    with open(project_dir_path+separator_character+'Makefile',"w") as makefile_copy: #creating a copy for Makefile
        makefile_copy.write(file_buffer)
        makefile_copy.close()
    
    with open(root+separator_character+'template'+separator_character+'.gitignore',"r") as f:
        file_buffer=f.read()
        f.close()
    with open(project_dir_path+separator_character+'.gitignore',"w") as gitignore_copy: #creating a copy for .gitignore
        gitignore_copy.write(file_buffer)
        gitignore_copy.close()
    
    with open(project_dir_path+separator_character+project_name+'.'+project_type,"w") as project_source: #creating the source file
        project_source.write(project_default_code)
        gitignore_copy.close()

    os.mkdir(project_dir_path+separator_character+'.vscode')
    with open(root+separator_character+'template'+separator_character+'c_cpp_properties.json',"r") as f:
        file_buffer=f.read()
        f.close()
    with open(project_dir_path+separator_character+'.vscode'+separator_character+'c_cpp_properties.json',"w") as properties_copy: #creating a copy for VS Code IntelliSense
        properties_copy.write(file_buffer)
        properties_copy.close()
else:
    print("Project already exists!")
