#!/usr/bin/env python

from setuptools import setup


with open('cal.py') as fh:
    docstring = []
    docstring_started = False
    docstring_done = False

    for line in fh:
        line = line.rstrip()

        if line.startswith('__version__ = '):
            version = line.strip()[15:-1]

        if docstring_started:
            if line == '"""':
                docstring_done = True
            elif not docstring_done:
                docstring.append(line)
        elif line.startswith('"""'):
            docstring_started = True
            docstring.append(line[3:])

    description = docstring[0]
    docstring = '\n'.join(docstring[2:])


setup(
    name='bsd-calendar',
    version=version,
    description=description,
    long_description=docstring,
    url='https://github.com/xi/calendar',
    author='Tobias Bengfort',
    author_email='tobias.bengfort@posteo.de',
    py_modules=['cal'],
    entry_points={'console_scripts': [
        'calendar=cal:main',
    ]},
    license='BSD',
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Environment :: Console',
        'Intended Audience :: End Users/Desktop',
        'Operating System :: OS Independent',
        'Programming Language :: Python :: 3.4',
        'License :: OSI Approved :: BSD License',
        'Topic :: Utilities',
    ])
