CREATE DATABASE Stack0verFl0w;
USE Stack0verFl0w;

CREATE TABLE User (
    id INT NOT NULL AUTO_INCREMENT,
    firstName VARCHAR(255),
    lastName VARCHAR(255),
    reputation DECIMAL(15,2),
    registerDate datetime,
    lastAccessDate datetime,
    birthdayDate datetime,

    PRIMARY KEY (id)
);

CREATE TABLE Category (
    id INT NOT NULL AUTO_INCREMENT,

    PRIMARY KEY (id)
);

CREATE TABLE Post (
    id INT NOT NULL AUTO_INCREMENT,
    owner INT NOT NULL,
    body VARCHAR(255),
    publishDate datetime,
    category INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (owner) REFERENCES User(id),
    FOREIGN KEY (category) REFERENCES Category(id)
);

CREATE TABLE AQ (
    id INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (id) REFERENCES Post(id)
);

CREATE TABLE Answer (
    id INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (id) REFERENCES AQ(id)
);

CREATE TABLE Question (
    id INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (id) REFERENCES AQ(id)
);

CREATE TABLE Comment (
    id INT NOT NULL,
    parent INT NOT NULL,

    PRIMARY KEY (id),
    FOREIGN KEY (id) REFERENCES Post(id),
    FOREIGN KEY (parent) REFERENCES AQ(id)
);

CREATE TABLE Vote (
    userId INT NOT NULL,
    postId INT NOT NULL,
    mark INT NOT NULL,

    PRIMARY KEY (userId, postId),
    FOREIGN KEY (userId) REFERENCES User(id),
    FOREIGN KEY (postId) REFERENCES Post(id),
    CHECK (mark = -1 OR mark = 1)
);
