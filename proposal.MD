## [Dataset](https://snap.stanford.edu/data/twitch_gamers.html)

- **Leading Question**: We have a few questions regarding our data for Twitch Streamers. Our primary question is to find whether there’s a clear relationship between overall time spent on twitch and followers. Specifically, we want to see if spending more time on twitch equates to a larger following. Another question we could consider is finding the user with the most mutual connections between two users. This could help us predict how mutual interactions/followings between multiple users can predict future followings. Additionally, we could find the average minimum user connection between any two users.

- **Dataset Acquisition and Processing**: We found our data using the provided Stanford data collection website. From there we found the publicly available Twitch Streamer data. Within the downloaded data file, there are two CSV files containing the data for streamers, and edges between the mutual follower relationships. Considering the size of the edges file, we will make small experimental files to test our code before processing the entirety of the Twitch Data. We will also have experimental files to test how errors within the data will affect our analysis.

- **Graph Algorithms**: We are planning to implement a BFS traversal in order to optimize neighboring-node searches, i.e. twitch users that follow the same streamers. For our covered algorithm, we are planning to use Dijkstra’s algorithm as a shortest-path finder between twitch user nodes, which will be our inputs. We expect the Dijkstra’s steps to run at O(m*Log(n)) complexity, where m is the number of edges and n is the number of nodes. For our uncovered algorithm, we are planning to use the PageRank algorithm. This will show which twitch user has the most connections between other twitch users, as they will end up as the highest PageRank. Future followings could then be predicted by what other users are following the higher PageRank. For PageRank we hope to have a target big O of O(n + m).

---

Timeline: The following timeline is based on our Saturday meetings and assigned project meetings.

- Final Project Proposal (Nov 8.)
Data acquired
1. Nov. 13
  - Basic C++ program can compile
  - README instructions began
  - Experimental CSV test Files Created
  - Program can read data from CSV files
2. Nov. 20
  - Begin Dijkstra’s algorithm
    - Test small parts of algorithm with smaller datasets
  - Begin PageRank algorithm
    - Test small parts of algorithm with smaller datasets
3. Nov. 27
  - Assure Dijkstra’s algorithm functions with larger datasets
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
