QLangAssist
===========
**QLangAssist** is a simple utility which helps you to learn new words while studying foreign language. It provides you with a window with multiple choices of translation for a particular word. When you have finished your testing it presents you with a dialog with a list of mistakes you've made during the test.

You should create a custom dictionary in your favorite plain text editor before using the program. *Use the UTF-8 encoding for the dictionary file!*

The dictionary format is quite simple :
<pre>
Word --- Translation
abrogate --- объявлять недействительным
fåtölj --- armchair
# comments start with hash character and not used in dictionary</td></tr>
...
</pre>

How to use
----------
Once you've prepared a dictionary, you can run the application. 
Every time the application starts it will ask you to choose the dictionary file; you may switch to another file during the application's runtime. 
The 'Close' [x] button hides the application to the system tray; you may show the window again by double-clicking to the application icon in system tray.
    
TODO
----
 * Create a simple editor to manage words in user's dictionary</li>
 * Add support for 'cheating' - find the word's translation instantly, not after the test</li>


----
*Copyright (c) 2010 Alexey Veretennikov <alexey dot veretennikov at gmail dot com>*
