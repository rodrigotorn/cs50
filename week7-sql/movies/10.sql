SELECT
    people.name
FROM
    movies JOIN
    directors on movies.id = directors.movie_id
    JOIN people ON directors.person_id = people.id
    JOIN ratings ON movies.id = ratings.movie_id
WHERE
    ratings.rating >= 9.0;