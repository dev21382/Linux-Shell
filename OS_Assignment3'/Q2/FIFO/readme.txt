P1.c :
  Here I have implemented a named pipe using mkfifo and have sent strings to   the P2 program in batches of 5 post which I am reading the returned value    from P2 with the help of simple read command from the buffer the       
  information was written into.

P2.c :
  Here I have opened the pipe so as to receive the strings and send the      
  highest string id back to P1.