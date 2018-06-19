# archi_lab7 </bn>
-----------------------------------
readelf- displays information about one or more ELF format object files.</br>
The options control what particular information to display.</br>
---------------------------------------------------------------
#task0 </br>
0a</br>
- changed the for stop con i<=arr.len -> i<arr.length.<br>
- added a FREE(X) func as shown in line_parser code.</br>
0b</br>
1-Where is the entry point specified, and what is its value? </br>
    Entry point address:               0x400110</br>
2-  How many sections are there in a.out? </br>

  Number of section headers:         8</br>
  3-  What is the size of the .text section? 
 </br> [ 1] .text             PROGBITS         00000000004000f0  000000f0</br>
       0000000000000062  0000000000000000  AX       0     0     16</br>
       the size is 62 bytes.</br>
  4-  Does the symbol _start occur in the file? If so, where is it mapped to in virtual memory? </br>
  </br>
  5-  Does the symbol main occur in the file? If so, where is it mapped to in virtual memory? </br>
  yes,     10: 00000000004000f0    29 FUNC    GLOBAL DEFAULT    1 main</br>
  mapped to : 00000000004000f0 .</br>
  6-  Where in the file does the code of function "_start" start? </br>
       7: 0000000000400110     0 NOTYPE  GLOBAL DEFAULT    1 _start</br>
       to calculate the entry of the _start needed :</br>
       entry_point+section_file_offset + function_virtual_address= 0x400110+4640+0000000000000018. </br>
-------------------------------------------------------------------------------------

       
