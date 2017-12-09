#!/bin/bash

if [ -s diffResult.dat ]
then 
        echo "Regression test failed: solution not identical"
else
        echo "Regression test passed"
fi
