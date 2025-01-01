from distutils.core import setup, Extension

setup(name='my_arr_lib',
    ext_modules=[
        Extension('my_arr_lib',
            ['./myarrlib.c'],
            include_dirs = ['.'],
            define_macros = [('FOO','1')],
            undef_macros = ['BAR'],
            library_dirs = ['.'],
            libraries = ['example']
            )
        ]
)
