# DEVELOPMENT LOG

## 11/13

We began this meeting by deciding more on the info on graphs to fix project proposal.

Our data seems to favor the adjacency matrix due to runtime
Instead of using a hash map, we are planning to use a vector. This may change along the way depending on how it works.


Mapping: 
- vertices in vector (our data is already sorted by increasing ID)
- adjancency matrix to store the edge relations between vertices

BFS Purpose:
- What should we return? We are plannig on using it as more of a tool, so it would depend on what we were doing with it.
- Will be used in PageRank algorithm
- Will take in a User ID and output neighbors

Second Algorithm:
- Graphic output of graph
- Thinking of the force-directed graph -- use the PageRank algorithm to find the node to center the graph around

Accomplishments Since Last Week:
- Makefile completed
- Contract approved
- Proposal Suggestions Made (addressed in this meeting, will be resubmitted)

Goals for Next Week:
- begin both algorithms (tentative)
- have our proposal approved
- getting the test data to connect with some code
- make a Twitch Streamer Class
- finish BFS (need it for other algorithms)

## 11/20 - 11/28 
Thanksgiving Break
- Test data created
- Graph class is functional
- PageRank class created and produces markov matricies
- Force-directed class skeleton created 

## 12/4

This meeting consisted of going over current progress, and future responsibilities such as testing, finalizing PageRank/Graph, and creating the final presentation. 

Accomplishments since last week:
- BFS in progress
- PageRank mostly done
- Experimental files done

Future Responsibilities
- Finalize BFS
- Finalize Force-Directed graph
- Have proper test

Goals for next week:
Finalize code by Friday so we can focus on the report and video by next weekend. Then we will have Monday as a buffer to submit everything by the deadline. 

##12/13

This week consisted of finalizing our project. 

By the meeting on Saturday, all algorithms/traversals except for Page Rank were complete. 

By Sunday, the Page Rank was completed. 

Today, we filmed the video and finalized the report.
 