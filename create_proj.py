#Used Python version Python 3.9.13
'''
This script shall be used to generate projects
Available extensions:.c and .s(assembly)
If none of the above extensions is provided,
the script shall default to .c
'''

import sys
import os

def get_help():
   print("Welcome to Hello-AVR project generator !")
   print("In order to properly create a project input a valid file extension and a name.")
   print("For example: py "+sys.argv[0]+" .c hello_world")
   print("Valid file extensions:")
   print("  .c:C source file")
   print("  .s:Assembly source file")

class GenerateProject: #interface
    def get_separator_character():
        pass

    def get_project_path(self,project_name):
        pass

    def generate_project(self):
        pass

class Project(GenerateProject):
    def __init__(self,project_name):

        self.default_code='Hello foo'
        self.project_name=project_name
        self.project_type='foo'
        self.project_dir=''

    def get_separator_character(self):
        if os.name =='nt':
            separator_character='\\'
            #Windows OS
        elif os.name =='posix':
            separator_character='/'
            #POSIX based OS
        return separator_character
    
    def get_project_path(self):
      separator_character=self.get_separator_character()
      return os.getcwd()+separator_character+self.project_dir+separator_character
    
    def generate_project(self):
        
        '''getting the root and separating character in order to fetch 
            files from 'template' directory'''
        root=os.getcwd()
        separator_character=self.get_separator_character()
        project_dir_path=self.get_project_path()+self.project_name

        if not os.path.exists(project_dir_path): #checking if the project has been created already

            os.mkdir(project_dir_path)

            #Creating the Makefile
            with open(root+separator_character+'template'+separator_character+'Makefile',"r") as f:
                file_buffer=f.read()
                f.close()
            with open(project_dir_path+separator_character+'Makefile','w') as makefile_copy:
                makefile_copy.write(file_buffer)
                makefile_copy.close()

            #Creating the .gitignore file
            with open(root+separator_character+'template'+separator_character+'.gitignore',"r") as f:
                file_buffer=f.read()
                f.close()
            with open(project_dir_path+separator_character+'.gitignore',"w") as gitignore_copy:
                gitignore_copy.write(file_buffer)
                gitignore_copy.close()

            #Creating the .vscode folder for IntelliSense
            os.mkdir(project_dir_path+separator_character+'.vscode')
            with open(root+separator_character+'template'+separator_character+'c_cpp_properties.json',"r") as f:
                file_buffer=f.read()
                f.close()
            with open(project_dir_path+separator_character+'.vscode'+separator_character+'c_cpp_properties.json',"w") as properties_copy:
                    properties_copy.write(file_buffer)
                    properties_copy.close()

            #Creating the source file
            with open(project_dir_path+separator_character+self.project_name+'.'+self.project_type,"w") as project_source:
                project_source.write(self.default_code)
                gitignore_copy.close()

        else:
            print("Project already exists!")
    
class CProject(Project):
    def __init__(self,project_name):
        super().__init__(project_name)
        self.default_code='''#include <avr/io.h>
        int main(void)
        {
        while (1) 
            {
            }
        }
        '''
        self.project_type='c'
        self.project_name=project_name
        self.project_dir='c'

class AssemblyProject(Project):        

    def __init__(self,project_name):
        super().__init__(project_name)
        self.default_code='''start:
        inc r16
        rjmp start'''
        self.project_type='s'
        self.project_name=project_name
        self.project_dir='asamblare'

if(len(sys.argv)==1):
    print("Error: no target file")
    print("Use py "+sys.argv[0]+' help in order to get more info')
else:
    if 'help' in sys.argv:
        get_help()
    elif '.c' in sys.argv:
        sys.argv.remove('.c')
        if(len(sys.argv)==1):
            print("Error: please also offer a project name")
        else:
            project=CProject(sys.argv[1])
            project.generate_project()
            print("Project created succesfully!")
    elif '.s' in sys.argv:
        sys.argv.remove('.s')
        if(len(sys.argv)==1):
            print("Error: please also offer a project name")
        else:
            project=AssemblyProject(sys.argv[1])
            project.generate_project()
            print("Project created succesfully!")
    else:
        print("Error: no valid inputs")
        print("Please use the help section in order to use the proper format.")
        print("py "+sys.argv[0]+" help")