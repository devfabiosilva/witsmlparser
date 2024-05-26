from distutils.core import setup, Extension

def main():

    setup(name="witsml14xbson",
        version="0.1.0",
        description="WITSML 1.4.x - 1.3.x BSON parser module for Python 3 using C library setup",
        author="Fábio Pereira da Silva",
        author_email="fabioegel@gmail.com",
        url="https://github.com/devfabiosilva/witsml14xbson",
        maintainer_email="fabioegel@gmail.com",
        ext_modules=[Extension("witsml14xbson", ["python/module.c", "stdsoap2.c"],
            library_dirs=['lib'],
            libraries=['cws_py', 'bson-shared-1.0'],
            extra_objects=[
            	"parser/w1411/delete/delete1411ServerLib_shared.o", "parser/w1411/read/read1411ServerLib_shared.o",
            	"parser/w1411/update/update1411ServerLib_shared.o", "parser/w1411/write/write1411ServerLib_shared.o"
            ],
            include_dirs=['include'],
            define_macros=[('CWS_LITTLE_ENDIAN', None), ('WITH_STATISTICS', None), ("WITH_NONAMESPACES", None), ("WITH_NOSERVEREQUEST", None)]
        )])

if __name__ == "__main__":
    main()

