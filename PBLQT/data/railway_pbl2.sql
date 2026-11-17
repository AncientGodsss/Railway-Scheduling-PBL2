-- =====================================================
-- DATABASE SCRIPT CHO DO AN PBL2: HE THONG DIEU PHOI LICH CHAY TAU
-- Phien ban chuan 21 ga & 20 tuyen truc Bac - Nam
-- =====================================================

DROP TABLE IF EXISTS stops;
DROP TABLE IF EXISTS schedules;
DROP TABLE IF EXISTS routes;
DROP TABLE IF EXISTS stations;
DROP TABLE IF EXISTS trains;

CREATE TABLE stations (
    station_id VARCHAR(20) PRIMARY KEY,
    station_name NVARCHAR(100) NOT NULL,
    location NVARCHAR(100),
    number_of_tracks INT NOT NULL DEFAULT 2
);

CREATE TABLE trains (
    train_id VARCHAR(20) PRIMARY KEY,
    train_name NVARCHAR(100) NOT NULL,
    train_type VARCHAR(20) NOT NULL,
    capacity INT NOT NULL,
    max_speed FLOAT NOT NULL,
    status VARCHAR(20) NOT NULL DEFAULT 'ACTIVE',
    note NVARCHAR(200)
);

CREATE TABLE routes (
    route_id VARCHAR(20) PRIMARY KEY,
    from_station_id VARCHAR(20) NOT NULL,
    to_station_id VARCHAR(20) NOT NULL,
    distance FLOAT NOT NULL,
    travel_time INT NOT NULL,
    status VARCHAR(20) NOT NULL DEFAULT 'ACTIVE',
    FOREIGN KEY (from_station_id) REFERENCES stations(station_id),
    FOREIGN KEY (to_station_id) REFERENCES stations(station_id)
);

CREATE TABLE schedules (
    schedule_id VARCHAR(20) PRIMARY KEY,
    train_id VARCHAR(20) NOT NULL,
    departure_station_id VARCHAR(20) NOT NULL,
    destination_station_id VARCHAR(20) NOT NULL,
    departure_time INT NOT NULL,
    arrival_time INT NOT NULL,
    priority INT NOT NULL DEFAULT 50,
    status VARCHAR(20) NOT NULL DEFAULT 'SCHEDULED',
    departure_date VARCHAR(20) NOT NULL,
    FOREIGN KEY (train_id) REFERENCES trains(train_id),
    FOREIGN KEY (departure_station_id) REFERENCES stations(station_id),
    FOREIGN KEY (destination_station_id) REFERENCES stations(station_id)
);

CREATE TABLE stops (
    schedule_id VARCHAR(20) NOT NULL,
    stop_order INT NOT NULL,
    station_id VARCHAR(20) NOT NULL,
    arrival_time INT NOT NULL,
    departure_time INT NOT NULL,
    PRIMARY KEY (schedule_id, stop_order),
    FOREIGN KEY (schedule_id) REFERENCES schedules(schedule_id),
    FOREIGN KEY (station_id) REFERENCES stations(station_id)
);

-- DU LIEU NHA GA
INSERT INTO stations (station_id, station_name, location, number_of_tracks) VALUES
('LAOCAI', N'Lào Cai', N'Miền Bắc', 3),
('LANGSON', N'Lạng Sơn', N'Miền Bắc', 3),
('HANOI', N'Hà Nội', N'Miền Bắc', 6),
('HAIPHONG', N'Hải Phòng', N'Miền Bắc', 4),
('NAMDINH', N'Nam Định', N'Miền Bắc', 3),
('NINHBINH', N'Ninh Bình', N'Miền Bắc', 3),
('THANHHOA', N'Thanh Hóa', N'Bắc Trung Bộ', 4),
('VINH', N'Vinh', N'Bắc Trung Bộ', 4),
('DONGHOI', N'Đồng Hới', N'Bắc Trung Bộ', 3),
('DONGHA', N'Đông Hà', N'Miền Trung', 3),
('HUE', N'Huế', N'Miền Trung', 3),
('DANANG', N'Đà Nẵng', N'Miền Trung', 5),
('QUANGNGAI', N'Quảng Ngãi', N'Duyên hải Nam Trung Bộ', 3),
('DIEUTRI', N'Diêu Trì', N'Nam Trung Bộ', 4),
('QUYNHON', N'Quy Nhơn', N'Nam Trung Bộ', 3),
('NHATRANG', N'Nha Trang', N'Nam Trung Bộ', 4),
('DAKLAK', N'Buôn Ma Thuột', N'Tây Nguyên', 2),
('THAPCHAM', N'Tháp Chàm', N'Nam Trung Bộ', 3),
('BINHTHUAN', N'Bình Thuận', N'Nam Trung Bộ', 3),
('BIENHOA', N'Biên Hòa', N'Miền Nam', 4),
('SAIGON', N'Sài Gòn', N'Miền Nam', 6);
