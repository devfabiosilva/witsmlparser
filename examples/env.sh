
search_dir=$(pwd)/../build/lib*

if [ -d $search_dir ]; then
 echo $(readlink -f $search_dir)
 export PYTHONPATH=$PYTHONPATH:$(readlink -f $search_dir)
 echo "Python path set to $PYTHONPATH"
else
 echo "ERROR: Py WITSML 1.3.x | 1.4.x to BSON parser not found. Compile module with 'make py' and run this environment again"
 return 1
fi

