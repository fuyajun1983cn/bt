#!/usr/bin/sh

rm -f *.html
rm -r objects.inv searchindex.js
rm -rvf _static
rm -rvf _sources 
cd source
make html
cd ..
cp -rvf html/* ./
rm -rvf doctrees
rm -rvf html
