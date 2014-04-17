Data-Science
===========


Raw data -> Processing script -> tidy data -> data analysis -> data communication

<h2>Getting and Cleaning the Data</h2>

Sources of data
<ul>
<li> APIs: twitter, ...</li>
<li> data.baltimorecity.gov </li>

</ul>


<h3> R commands: Getting data</h3>

```
file.exists("somefile")
dir.create("newdirectory")

if (!file.exists("data")) {
  dir.create("date")
}

download.file(url, destfile, method)
```
