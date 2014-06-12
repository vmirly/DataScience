Converting Markdown Document to HTML
===================================

# Introduction

This is a test example, illustrating how to convert a 
markdown document to a HTML file.

# Code-blocks:

Code-blocks have to be indented 4 white spaces. For example, like the following:

    import numpy as np
    arr = np.array([1, 2, 3])
    print (arr.shape)

# Generate Output HTML

So to generate output HTML file, use the following command:

    python -m markdown mymarkdown.md > mydoc.html
