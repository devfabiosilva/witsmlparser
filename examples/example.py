import bson
import witsml14xbson

# HOW TO RUN:
# In source directory:
#######################
# make -j12 py        #
# cd examples         #
# sourse env.sh       #
# python3 example.py  #
#######################

def main():
    parser1 = witsml14xbson.create() # Create default instance: Action READ and Schema version check enabled
    parser2 = witsml14xbson.create(versionCheckDisable = True) # Create Read instance disabling Schema check
    parser2 = witsml14xbson.create(witsml14xbson.ACTION_READ_141X) # Default READ rule with Schema version enabled
    parser3 = witsml14xbson.create(witsml14xbson.ACTION_READ_141X, True) # Version check disable. Disable check Schema version
    parser4 = witsml14xbson.create(witsml14xbson.ACTION_READ_141X, False) # Check Schema version

def loadFiles():
    # TODO
    pass

if __name__ == "__main__":
    main()

