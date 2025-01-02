from distutils.core import setup, Extension

setup(name='my_arr',
    version='0.0.1',
    description = "Test lib. I port functions from lab_12 to python with library and expansion module",
    ext_modules=[
        Extension('my_arr_lib',
            ['./src/myarrlib.c'],
            include_dirs = ['./inc/'],            
            define_macros = [('FOO','1')],
            undef_macros = ['BAR'],
            library_dirs = ['./out/'],
            libraries = ['my_arr']
            )
        ]
)
