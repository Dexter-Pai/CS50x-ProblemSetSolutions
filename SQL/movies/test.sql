SELECT id FROM people WHERE name = 'Johnny Depp' OR name = 'Helena Bonham Carter';
SELECT movie_id FROM stars JOIN
SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Johnny Depp');
SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = 'Johnny Depp') AND person_id IN (SELECT id FROM people WHERE name = 'Helena Bonham Carter');
SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter');
SELECT count(DISTINCT movie_id) FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = 'Helena Bonham Carter') AND person_id IN (SELECT id FROM people WHERE name = 'Johnny Depp');
SELECT count(DISTINCT movie_id) FROM stars WHERE person_id IN ((SELECT id FROM people WHERE name = 'Helena Bonham Carter'), (SELECT id FROM people WHERE name = 'Johnny Depp'));
SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Johnny Depp')) ORDER BY title ASC;
SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter')) ORDER BY title ASC;
SELECT title FROM movies WHERE id IN (SELECT id FROM people WHERE name = 'Johnny Depp') AND id IN (SELECT id FROM people WHERE name = 'Helena Bonham Carter');


SELECT id, name, birth FROM people WHERE name = 'Kevin Bacon' AND birth = '1958';


#Kevin Bacon starred in these movies
SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958');
SELECT person_id FROM stars WHERE movie_id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958'));

