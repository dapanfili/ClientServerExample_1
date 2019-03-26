Author: Tim Lindquist (Tim.Lindquist@asu.edu)
        Software Engineering, CIDSE, IAFSE, Arizona State University Polytechnic
Version: June 2015

See http://pooh.poly.asu.edu/Ser321

Purpose: Sample project showing C++ JsonRPC server and client for simple
calculator. The project includes a Java client to the JsonRPC C++ server.
Both clients are command-line programs that read simple expressions from
standard in (terminal) and use the server to compute the result.

The Java client does the Json encoding using Douglas Crockford's JSON-Java
library which you can download from:

https://github.com/douglascrockford/JSON-java

The classes from this library are included in the lib directory of this project
in the jar file: json.jar. Nevertheless, you should download the library and
generate the javadocs for the classes, which will be useful in completing
Assignments 3, 4, and 5. See the setup page at:

http://pooh.poly.asu.edu/Ser321/Resources/setupJsonJavaNJsonRPCcpp.html

C++ programs implement the server and client for JsonRPC calculator. These
programs rely on the library package libjson-rpc-cpp

After building and installing libjson-rpc-cpp, to build the C++ server enter:
ant build.server
from the command line. To build the C++ client use:
ant build.client

To build the sample Java client:
ant build.java.client

The C++ server and client are built in the bin directory. Execute the server
first and then from a separate terminal execute the client.

On Linux, RPi, or MacOSX, execute the Java client with:
java -cp classes:lib/json.jar ser321.jsonrpc.CalcJavaClient http://localhost:8080

Completing assignments 3, 4, and 5 will require the following frameworks:
FLTK toolkit, libjson-rpc-cpp, and JSON-Java. Instructions for building FLTK
can be found at the class web site:
http://pooh.poly.asu.edu/Ser321/Resources/setupFLTK.html

Depending on your installation of Ant, you may need to place cpp tasks,
and ant-contrib tasks for Ant where it will find them.
This project's lib directory contains the java archive:

antlibs.jar

Copy that jar file to your home directory and extract its contents with:

jar xf antlibs.jar

If after extracting the above, you still get an error (if task not found)
when doing ant build.cpp.tasks then copy the task definition files directly
to the lib directory of your ant installation:

cp ./.ant/libs/*.jar $ANT_HOME/lib/

Be sure that ANT_HOME is properly defined before using the copy above.

The project directory contains some two sample JsonRPC commmands in the files:
sampleSubtract.json
sampleAdd.json

There is also a shell command in sampleCurlCommandAdd.sh
To use the curl command on MacOSX, do the following:
chmod u+x sampleCurlCommandAdd.sh
./sampleCurlCommandAdd.sh

The file calculate.json is a json array whose elements are json objects. Each
object in the array provides the signature for a method implemented by the
jsonrpc server. calculate.json is used by the libjson-rpc-cpp proxy generator
tool in generating the client and server side stubs.
