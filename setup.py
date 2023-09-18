from setuptools import Extension, setup 

ext = Extension("interp", ["interp_api.cpp"])

setup(
        name="interp",
        ext_modules=[ext]
        )
