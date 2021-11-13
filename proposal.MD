## [Dataset](https://snap.stanford.edu/data/twitch_gamers.html)

**Leading Question**: Our primary question is to find whether there’s a clear relationship between overall time spent on twitch and followers. Specifically, we want to see if users with an early creation date are most likely to be followed, as described by the Pagerank algorithm. 

**Dataset Acquisition and Processing**: We found our data using the provided Stanford data collection website. From there we found the publicly available Twitch Streamer data. Within the downloaded data file, there are two CSV files containing the data for streamers, and edges between the mutual follower relationships.

We will have a vector to store our vertices and it’s respective data. Fortunately, our data has a zero-indexed id system that is already sorted. We will also have an adjacency matrix to store the edge relations between our vertices (streamers). 

Considering the size of the edges file, we will make small experimental files to test our code before processing the entirety of the Twitch Data. We will also have experimental files to test how errors within the data will affect our analysis. 


**Graph Algorithms**: We are planning to implement a BFS traversal in order to optimize neighboring-node searches, i.e. twitch users that follow the same streamers. Our BFS traversal will input a user ID to search for and output the neighboring nodes. Since our dataset is strongly connected around centered vertices, we can use BFS for efficient traversing in our algorithms.

For our first algorithm, we are planning to use PageRank. PageRank will tell us which twitch users will have the highest probability to be clicked on. This probability is directly related to the amount of followers they have (More followers = higher probability to be clicked on). For PageRank we hope to have a target big O of O(n + m). 

For our second algorithm, we will make a graphic output of our graph. We will make a Force-directed graph based on our PageRank analysis of what twitch streamers are the most important. The streamer with the highest probability determined by PageRank will be in the center of the page and the followers will be near the edges of the canvas. If possible, we will try to use more PageRank data to spread out the streamers with the highest importance. 

Timeline: The following timeline is based on our Saturday meetings and assigned project meetings.

- Final Project Proposal (Nov 8.)
Data acquired
1. Nov. 13
  - Basic C++ program can compile
  - README instructions began
  - Experimental CSV test Files Created
  - Program can read data from CSV files
2. Nov. 20
  - Begin Force-Directed Graph algorithm
    - Test small parts of algorithm with smaller datasets using arbitrary center
  - Begin PageRank algorithm
    - Test small parts of algorithm with smaller datasets
3. Nov. 27
  - Assure Force-Directed Graph algorithm functions with larger datasets
    - Test edge cases
  - Assure PageRank algorithm functions with larger datasets
    - Test edge cases
- Mid-Project Check-in (Nov 29th – Dec 1)

4. Dec. 4
  - All algorithms complete
  - Functional Code Base Complete
  - Stretch Goal: implement a visual representation of the data
5. Dec. 11
  - Project Video Complete
  - Project Report Complete
  - README instructions complete
- Final Project Deliverables (Due Dec 13th)
