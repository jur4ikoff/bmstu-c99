from distutils.core import setup, Extension

setup(name='example_dylib',
    ext_modules=[
        Extension('example_dylib',
            ['wrap.c'],
            include_dirs = ['.'],
            define_macros = [('FOO','1')],
            undef_macros = ['BAR'],
            library_dirs = ['.'],
            libraries = ['example']
            )
        ]
)
