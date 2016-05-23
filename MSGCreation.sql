CREATE TABLE decoupages(
	id INTEGER PRIMARY KEY AUTOINCREMENT, 
	nom VARCHAR, 
	x INTEGER NOT NULL, 
	y INTEGER NOT NULL, 
	width INTEGER NOT NULL, 
	height INTEGER NOT NULL,
	jour VARCHAR,
	heure VARCHAR,
	quartDheur VARCHAR,
	dateCreated DATETIME DEFAULT CURRENT_TIMESTAMP,
	chemin VARCHAR
	); 
 
CREATE INDEX decoupagesIndexOnNom
ON decoupages (nom);

CREATE INDEX decoupagesIndexOnDateCreated
ON decoupages (dateCreated);

CREATE TABLE images(
	id INTEGER PRIMARY KEY AUTOINCREMENT, 
	decoupageId INTEGER,
	canal VARCHAR,
	chemin VARCHAR NOT NULL,
	FOREIGN KEY (decoupageId) REFERENCES decoupages(id)
	);
		
CREATE INDEX imagesIndexOnDecoupageId
ON images (decoupageId);
	

CREATE TABLE communes(
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	WILAYA varchar,
	COMMUNE varchar NOT NULL,
	NATURE varchar,
	pop1987 INTEGER,
	pop1998 INTEGER,
	code_commune VARCHAR,
	Longitude REAL NOT NULL,
	Latitude REAL NOT NULL
	);

CREATE INDEX communeIndexOnWILAYA
ON communes (WILAYA);

CREATE INDEX communeIndexOnCOMMUNE
ON communes (COMMUNE);

CREATE INDEX communeIndexOnCode_commune
ON communes (code_commune);