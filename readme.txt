Command line tool which accepts multiple files as arguments and four different flags to indicate which function to perform.




Functions:

 -a [archiver]: [executable] -a [archive] [file0, ... ,fileN] Places listed files into specified archive.



-u [unpacker]: [executable] -u [archive] Unpacks given archive, creating specified files in current directory



-l [list]: [executable] -l [archive] Lists information about given archive (number of files within, size of archive, list of file names as well as file sizes)



-v [verify]: [executable] -v [archive] [file0, ... , fileN] Verifies that the given archive contains the specified files in the order given. This checks that the data within the archive is not corrupted nor missing bytes.