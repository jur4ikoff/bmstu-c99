from distutils.core import setup, Extension

setup(name='my_arr_lib',
    ext_modules=[
        Extension('libmy_arr',
            ['./src/myarrlib.c'],
            include_dirs = ['./inc/'],            
            define_macros = [('FOO','1')],
            undef_macros = ['BAR'],
            library_dirs = ['./out/'],
            libraries = ['my_arr']
            )
        ]
)
