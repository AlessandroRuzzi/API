# API Project
:small_blue_diamond: This is my proposed solution for the final assignment of the API (Algoritmi e Principi dell'Informatica) course that got the max score.

# Description
![alt text](Docs/social-network.jpg?raw=true)
<br/>
:small_blue_diamond: The aim of the project is to implement a simple system for monitoring relationships between entities. The program must be implemented in C11, using only the standard library (libc) and the base runtime.<br/>

The program that implements the system will receive an input of the relations from stdin and will print the report on stdout.<br/>

The project assignment PDF (in Italian) can be found [here](Docs/ProvaFinale2019.pdf).<br/>



# How it Works

There are 6 type of functions:
1. Addent<br/>
2. Addrel<br/>
3. Delrel <br/>
4. Delent <br/>
5. Report <br/>
6. End <br/>


### 1. Addent:walking:

<br/>
:small_blue_diamond:Adds an entity identified by "id_ent" to the set of monitored entities; If the entity is already monitored, it does nothing.<br/><br/>

### 2. Addrel:couple:

<br/>
:small_blue_diamond:Adds a relation identified by "id_rel" between the "id_orig" and "id_dest" entities, where "id_dest" is the receiver of report. 
<br/>If the relationship between "id_orig" and "id_dest" already exists, or if at least one of the entities is not monitored, it does nothing. 
<br/>Monitoring of the "id_rel" relationship type begins implicitly with the first "addrel" command concerning it.<br/><br/>

### 3. Delrel:put_litter_in_its_place:

<br/>
:small_blue_diamond:Removes the relationship identified by "id_rel" between the entities "id_orig" and "id_dest" (where "id_dest" is the receiver ofreport); 
<br/>If there is no "id_rel" relationship between "id_orig" and "id_dest" (with "id_dest" as the receiver), it does nothing.<br/><br/>

### 4. Delent:no_pedestrians:

<br/>
:small_blue_diamond:Delete the entity identified by "id_ent" from the set of monitored entities; Delete all the relations whose "id_ent" does part (both in origin and destination).<br/><br/>

### 5. Report:earth_africa:

<br/>
:small_blue_diamond:It outputs the list of relations, reporting for every relations the entity with the largest number of received relations.<br/><br/>

### 6. End:triangular_flag_on_post:

<br/>
:small_blue_diamond:End of the command sequence.<br/><br/>

# License

:books: This project is distributed under the terms of the MIT License. See file [LICENSE](LICENSE) for further reference.
