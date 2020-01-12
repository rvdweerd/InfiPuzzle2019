# InfiPuzzle2019
aoc.infi.nl 2019. De kerstman springt over de daken. Mooie coding challenge.
Heb hem (nogal inefficient) opgelost met een tree met branches voor iedere unieke mogelijke route, O(2^N) (totale energie sla ik op in de Nodes struct). </br>Zie comments in main() </br>

Ideeen voor beter alternatief: BFS als ik een unweighted chart kan bedenken, anders Dijkstra? Dan hoef je niet meer alle nodes van de chart (alle mogelijke tussenstops van alle mogelijke routes) te ontrafelen..

12/1/2020: Inmiddels twee aanvullende benaderingen geimplementeerd:</br>

Oplossing #2. Bouwt graph met alle unieke routes (nodes en directed arcs); waarop Dijkstra wordt toegepast -> [repo oplossing 2](https://github.com/rvdweerd/InfiPuzzle2019_solution2.git)</br>

Oplossing #3. 3. Bouwt graph (nodes en directed arcs) terwijl we Dijkstra toepassen. Dit is de meest efficiente toepassing want alleen het strikt nodige werk wordt gedaan. -> [repo oplossing 3](https://github.com/rvdweerd/InfiPuzzle2019_solution3.git)
