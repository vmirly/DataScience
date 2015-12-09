Installing Hadoop on Ubuntu
===========

1. Install **Java**

```
   vmirly@ubuntu:~$ sudo apt-get update

   vmirly@ubuntu:~$ sudo apt-get install default-jdk

   # Check Java version
   vmirly@ubuntu:~$ java -version
   java version "1.7.0_91"
   OpenJDK Runtime Environment (IcedTea 2.6.3) (7u91-2.6.3-0ubuntu0.15.04.1)
   OpenJDK 64-Bit Server VM (build 24.91-b01, mixed mode) 
```

2. Add a **user** and assign it to hadoop group

```
   vmirly@ubuntu:~$ sudo addgroup hadoop

   vmirly@ubuntu:~$ sudo adduser --ingroup hadoop hduser
```

3. Install **sshd**

```
   vmirly@ubuntu:~$ sudo apt-get install sshd

   # check installation to see if sshd is running
   vmirly@ubuntu:~$ which sshd
   /usr/sbin/sshd
```

4. Configure **ssh** for passwordless entry

```
   vmirly@ubuntu:~$ su hduser
   hduser@ubuntu:~$ ssh-keygen -t rsa 
   # save the file under /home/hduser/.ssh/hadoop
   # don't add any passphrase for convenience

   # Copy the public key to authorized_keys file
   cat /home/hduser/.ssh/hadoop.pub > /home/hduser/.ssh/authorized_keys

   hduser@ubuntu:~$ eval `ssh-agent`
   Agent pid 5654
   hduser@ubuntu:~$ ssh-add /home/hduser/.ssh/hadoop
   Identity added: /home/hduser/.ssh/hadoop (rsa w/o comment)
```

Check the ssh configuration:

```
   hduser@ubuntu:~$ ssh localhost
```

5. Download and Configure **Hadoop** Installation

Download *hadoop common* from this link: http://www.apache.org/dyn/closer.cgi/hadoop/common/

```
```
