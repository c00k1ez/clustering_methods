import pybind11
from setuptools import Extension, find_packages, setup


ext_modules = [
    Extension(
        'clustering_methods_', 
        [
        	'clustering_methods/cpp/bind.cpp', 
        	'clustering_methods/cpp/KMeans.cpp'
        ],
        include_dirs=[pybind11.get_include()],
        language='c++', 
        extra_compile_args=['-std=c++11'],
    ),
]

setup(
    name='clustering_methods',
    version='0.0.1',
    packages=find_packages(),
    author='Egor Plotnikov',
    author_email='egorplotnikov18@gmail.com',
    description='Small library with k-means realization.',
    ext_modules=ext_modules,
    install_requires=["pybind11>=2.4.3"],
    requires=['pybind11'], 
    #package_dir = {'': 'clustering_methods/lib'},
    classifiers=[
    'Development Status :: 3 - Alpha',      
    'Intended Audience :: Developers',      
    'Topic :: Software Development :: Build Tools',
    'License :: OSI Approved :: MIT License',   
    'Programming Language :: Python :: 3',      
    'Programming Language :: Python :: 3.4',
    'Programming Language :: Python :: 3.5',
    'Programming Language :: Python :: 3.6',
  ]
)