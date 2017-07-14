# files_MultiWayMergesort
Implementation of multi-way mergesort for sorting a file containing records.

# File organization

- File contains records of Person objects
- Each Person has: Name (string) & ID (integer)
- ID is stored first, and uses up the space of a *long int*
- Name is written up to, and including, the `\0` character.

# Test file

 - Randomly generated.
 - Names have between 1 and 100 randomly generated characters between ascii 'A' and 'Z'.
 - 10,000,000 records. 344 MB.
