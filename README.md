Use arrows to move in Write and Navigation modes
Use PageUp and PageDown to move one page up or down
in Navigation mode type 'gg' to move to the first page
                        'G' to move to the last page

Navigation mode:
    i	Enter text before the cursor.
    I	Go to the beginning of the line and start entering text.
    S	Go to the end of the line and start typing.
    A	Delete the contents of the row and start typing.
    r	Replace one character under the cursor.
    :	Activating the command input mode.
    /	Activates search mode until the end of the document.
    ?	Activates search mode until the start of the document.

    ^	Moves the cursor to the start of the line.
    $	Moves the cursor to the end of the line.
    w	Move the cursor to the end of a word to the right of the cursor
    b	Move the cursor to the beginning of the word to the left of the cursor
    x	Delete the character after the cursor.
    diw	Delete the word under the cursor, including one space on the right.
    dd	Cut (copy and delete) the current line.
    y	Copy the current line.
    yw	Copy the word under the cursor.
    p	Insert after the cursor.
    NG	Go to the line with the number N.

Search mode:
    / <text>    Search for the <text> string from the cursor to the end of the file.
    ? <text>	Search for the <text> string from the cursor to the beginning of the file.

    n	Repeat search forward.
    N	Repeat search back.

Command mode:
    o <filename>	Open the file <filename>.
    x	Write to the current file and close it.
    w	Write to the current file.
    w <filename>	Write to file <filename>.
    q	Exit program.
    q!	Exit program without saving current file.
    wq!	Write to the current file and close it.
    num	Go to the line with the number <num>.
    h	Program help.
