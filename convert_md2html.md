Converting Markdown Document to HTML
===================================

# 1. Introduction

This is a test example, illustrating how to convert a 
markdown document to a HTML file.

# 2. Code-blocks:

Code-blocks have to be indented 4 white spaces. For example, like the following:

    import numpy as np
    arr = np.array([1, 2, 3])
    print (arr.shape)

# 3. Generate Output HTML

So to generate output HTML file, use the following command:

    python -m markdown mymarkdown.md > mydoc.html

# 4. Highlighting Python Syntax

So, in order to highlight python codes, use this option **-x codehilite** as below:

    python -m markdown -x codehilite mymarkdown.md > mydoc.html
