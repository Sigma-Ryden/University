drop database if exists `aero`;
create database if not exists `aero`;

use `aero`;

create table if not exists `aero`.`bookings` (
  `book_ref` 		varchar(40) not null,
  `book_data` 		datetime,
  `total_amount` 	decimal(11, 2),
  
  primary key (`book_ref`)
);

create table if not exists `aero`.`tickets` (
  `ticket_no` 		int not null,
  `book_ref` 		varchar(40) not null,
  `passenger_id` 	int not null,
  `passenger_name` 	varchar(20) not null,
  `contact_data` 	varchar(20) not null,
  
  primary key (`ticket_no`, `book_ref`),
  
  index			 	`fk_tickets_bookings_idx` (`book_ref`),
  constraint	 	`fk_tickets_bookings` foreign key (`book_ref`) references `aero`.`bookings` (`book_ref`)
);

create table if not exists `aero`.`airports` (
  `airport_code` 	int not null,
  `airport_name` 	varchar(30) not null,
  `city` 			varchar(30) not null,
  `longitude` 		varchar(20) not null,
  `latitude` 		varchar(20) not null,
  `timezone` 		time,
  
  primary key (`airport_code`)
)
engine = InnoDB;

create table if not exists `aero`.`aircrafts` (
  `aircraft_code` 	int not null,
  `range` 			int not null check (`range` > 0 and `range` <= 10),
  `model` 			varchar(20) not null,
  
  primary key (`aircraft_code`)
);

create table if not exists `aero`.`seats` (
  `seat_no` 			int not null check (`seat_no` > 0 and `seat_no` <= 300),
  `aircraft_code` 		int not null,
  `fare_conditions` 	enum('low', 'medium', 'hight') not null,
  
  primary key (`seat_no`, `aircraft_code`),
  
  unique index 			`seat_no_UNIQUE` (`seat_no`),
  index 				`fk_seats_aircrafts_idx` (`aircraft_code`),
  constraint 			`fk_seats_aircrafts` foreign key (`aircraft_code`) references `aero`.`aircrafts` (`aircraft_code`)
);

create table if not exists `aero`.`flights` (
  `flight_id` 			int not null auto_increment,
  `flight_no` 			int,
  `aircraft_code` 		int not null,
  `airport_code` 		int not null,
  `scheduled_departure` datetime,
  `scheduled_arrival` 	datetime,
  `departure_airport` 	varchar(30) not null,
  `arrival_airport` 	varchar(30) not null,
  `actual_departure` 	datetime,
  `actual_arrival` 		datetime,
  `status` 				bool default false,
  
  primary key (`flight_id`),
  
  unique index			`flight_no_UNIQUE` (`flight_no`),
  index 				`fk_flights_aircrafts_idx` (`aircraft_code`),
  index 				`fk_flights_airports_idx` (`airport_code`),
  constraint 			`fk_flights_aircrafts` foreign key (`aircraft_code`) references `aero`.`aircrafts` (`aircraft_code`),
  constraint 			`fk_flights_airports` foreign key (`airport_code`) references `aero`.`airports` (`airport_code`)
);

create table if not exists `aero`.`ticket_flights` (
  `ticket_no` 			int not null,
  `flight_id` 			int not null,
  `fare_conditions` 	enum('low', 'medium', 'hight') not null,
  `amount`			 	DECIMAL(11, 2),
  
  primary key (`ticket_no`, `flight_id`),
  
  index 				`fk_ticket_flights_flights_idx` (`flight_id`),
  constraint 			`fk_ticket_flights_flights` foreign key (`flight_id`) references `aero`.`flights` (`flight_id`),
  constraint 			`fk_ticket_flights_ticktes` foreign key (`ticket_no`) references `aero`.`tickets` (`ticket_no`)
);

create table if not exists `aero`.`boarding_passes` (
  `flight_id` 		int,
  `ticket_no` 		int not null,
  `boarding_no` 	int not null,
  `seat_no` 		int not null check (`seat_no` > 0 and `seat_no` <= 300),
  
  unique index 		`flight_id_UNIQUE` (`flight_id`),
  unique index 		`boarding_no_UNIQUE` (`boarding_no` ),
  unique index 		`seat_no_UNIQUE` (`seat_no`),
  index 			`fk_boarding_passes_ticket_flights_idx` (`ticket_no`),
  constraint 		`fk_boarding_passes_ticket_flights` foreign key (`ticket_no`) references `aero`.`ticket_flights` (`ticket_no`)
);


insert into `bookings` (`book_ref`, `book_data`, `total_amount`) values
('Tom Harison', '2021-12-03 04:23:19', 1500.0),
('Jack London', '2021-02-05 04:28:06', 1700.0),
('Jonny Seens', '2021-11-04 07:13:21', 1450.0);

insert into `aircrafts` (`aircraft_code`, `range`, `model`) values
(62442, 8, 'Mria'),
(42314, 9, 'Loran'),
(24821, 7, 'Tiny');

insert into `tickets` (`ticket_no`, `book_ref`, `passenger_id`, `passenger_name`, `contact_data`) values
(1, 'Jack London', 1412, 'Harly Queen', '0937713242'),
(2, 'Jonny Seens', 3242, 'Steev Jen', '0982347142');

insert into `seats` (`seat_no`, `aircraft_code`, `fare_conditions`) values
(124, 24821, 'medium'),
(259, (select aircraft_code from aircrafts where aircraft_code = 62442), 'low'),
(184, (select aircraft_code from aircrafts where aircraft_code = 24821), 'medium');

insert into `airports` (`airport_code`, `airport_name`, `city`, `longitude`, `latitude`, `timezone`)
values (81242, 'Kira', 'Odessa', '-0.93841 8.124231', '-0.91284 0.81238', '12:00:00');

insert into `flights` (`flight_id`, `flight_no`, `aircraft_code`, `airport_code`, `scheduled_departure`,
  `scheduled_arrival`, `departure_airport`, `arrival_airport`, `actual_departure`, `actual_arrival`, `status`) values
(1, 1, 62442, 81242, '2021-12-03 04:23:19', '2021-12-03 06:23:19', 'adf', 'asaf', '2021-12-03 04:23:19', '2021-12-03 04:23:19', true);

insert into `ticket_flights` (`ticket_no`, `flight_id`, `fare_conditions`, `amount`) values
(1, 1, 'low', 1500.0); 

#select * from ticket_flights;

select city from airports where airport_code = (
select airport_code from flights where flight_id = (
select flight_id from ticket_flights where ticket_no = (
select ticket_no from tickets where passenger_name = 'Harly Queen')));
