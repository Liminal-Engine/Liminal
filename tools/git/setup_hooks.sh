#! /bin/bash

cd $(dirname $0)
cp hooks/pre-commit ../../.git/hooks/pre-commit
chmod +x ../../.git/hooks/pre-commit
echo "pre-commit hook installed"