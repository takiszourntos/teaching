############# the # special character

# this line is a comment

ls -l # can also place a comment after a command 

# note the whitespace between the command and the hash sign

	# comments can follow whitespace at the beginning of line 
	# for more info on whitespace, see https://tldp.org/LDP/abs/html/special-chars.html#WHITESPACEREF

# Note the variations within quotes:
echo "The # here does not begin a comment."
echo 'The # here does not begin a comment.'
echo The \# here does not begin a comment.
echo The # here begins a comment.

# we'll say more about quotes in a bit

############# the * and ? special characters

# often used as wild card characters in globbing

ls -l t?.sh

ls -l *.sh

############# the ; special character

# as a command separator
echo hello; echo there; ls -l; date

# in an if-statement 
if [ -x "$filename" ]; then    #  Note the space after the semicolon.
#+                   ^^
  echo "File $filename exists."; cp $filename $filename.bak
else   #                       ^^
  echo "File $filename not found."; touch $filename
fi; echo "File test complete."


############# the \ (escape) special character

# certain special characters

# \n : newline
# \r : return
# \t : tab
# \v : vertical tab
# \b : backspace
# \a : alert
# \$ : literal dollar sign
# \" : literal quotation mark






