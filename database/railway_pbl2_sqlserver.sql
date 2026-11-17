-- ============================================================
-- SCRIPT SQL SERVER (SSMS): HE THONG QUAN LY LICH CHAY TAU (PBL2)
-- Server: ANCTGDS\SQLEXPRESS
-- ============================================================

-- 1. TAO DATABASE MOI
IF NOT EXISTS (SELECT * FROM sys.databases WHERE name = 'Railway_PBL2')
BEGIN
    CREATE DATABASE Railway_PBL2;
END
GO

USE Railway_PBL2;
GO

-- 2. XOA BANG CU NEU DA TON TAI (Theo thu tu khoa ngoai)
IF OBJECT_ID('stops', 'U') IS NOT NULL DROP TABLE stops;
IF OBJECT_ID('operations', 'U') IS NOT NULL DROP TABLE operations;
IF OBJECT_ID('schedules', 'U') IS NOT NULL DROP TABLE schedules;
IF OBJECT_ID('routes', 'U') IS NOT NULL DROP TABLE routes;
IF OBJECT_ID('stations', 'U') IS NOT NULL DROP TABLE stations;
IF OBJECT_ID('trains', 'U') IS NOT NULL DROP TABLE trains;
GO

-- 3. TAO BANG TRAINS (Doan tau)
CREATE TABLE trains (
    train_id VARCHAR(20) PRIMARY KEY,
    train_name NVARCHAR(100) NOT NULL,
    train_type NVARCHAR(50) NOT NULL,
    capacity INT NOT NULL CHECK (capacity > 0),
    max_speed FLOAT NOT NULL CHECK (max_speed > 0),
    status NVARCHAR(30) NOT NULL DEFAULT 'ACTIVE'
);

-- 4. TAO BANG STATIONS (Nha ga)
CREATE TABLE stations (
    station_id VARCHAR(20) PRIMARY KEY,
    station_name NVARCHAR(100) NOT NULL,
    location NVARCHAR(100) NOT NULL,
    number_of_tracks INT NOT NULL CHECK (number_of_tracks > 0)
);

-- 5. TAO BANG ROUTES (Tuyen duong noi truc tiep giua 2 ga)
CREATE TABLE routes (
    route_id VARCHAR(20) PRIMARY KEY,
    from_station_id VARCHAR(20) NOT NULL,
    to_station_id VARCHAR(20) NOT NULL,
    distance FLOAT NOT NULL CHECK (distance > 0),
    travel_time INT NOT NULL CHECK (travel_time > 0),
    status NVARCHAR(30) NOT NULL DEFAULT 'ACTIVE',
    CONSTRAINT FK_Route_From FOREIGN KEY (from_station_id) REFERENCES stations(station_id),
    CONSTRAINT FK_Route_To FOREIGN KEY (to_station_id) REFERENCES stations(station_id)
);

-- 6. TAO BANG SCHEDULES (Lich chay tau)
CREATE TABLE schedules (
    schedule_id VARCHAR(20) PRIMARY KEY,
    train_id VARCHAR(20) NOT NULL,
    departure_station_id VARCHAR(20) NOT NULL,
    destination_station_id VARCHAR(20) NOT NULL,
    departure_time INT NOT NULL CHECK (departure_time >= 0),
    arrival_time INT NOT NULL CHECK (arrival_time >= 0),
    priority INT NOT NULL DEFAULT 50,
    status NVARCHAR(30) NOT NULL DEFAULT 'SCHEDULED',
    departure_date VARCHAR(20) NOT NULL,
    CONSTRAINT FK_Schedule_Train FOREIGN KEY (train_id) REFERENCES trains(train_id),
    CONSTRAINT FK_Schedule_From FOREIGN KEY (departure_station_id) REFERENCES stations(station_id),
    CONSTRAINT FK_Schedule_To FOREIGN KEY (destination_station_id) REFERENCES stations(station_id)
);

-- 7. TAO BANG STOPS (Cac diem dung tren lich trinh)
CREATE TABLE stops (
    schedule_id VARCHAR(20) NOT NULL,
    stop_order INT NOT NULL CHECK (stop_order > 0),
    station_id VARCHAR(20) NOT NULL,
    arrival_time INT NOT NULL CHECK (arrival_time >= 0),
    departure_time INT NOT NULL CHECK (departure_time >= 0),
    PRIMARY KEY (schedule_id, stop_order),
    CONSTRAINT FK_Stop_Schedule FOREIGN KEY (schedule_id) REFERENCES schedules(schedule_id) ON DELETE CASCADE,
    CONSTRAINT FK_Stop_Station FOREIGN KEY (station_id) REFERENCES stations(station_id)
);

-- 8. TAO BANG OPERATIONS (Lich su dieu phoi / Tranh tau)
CREATE TABLE operations (
    operation_id INT IDENTITY(1,1) PRIMARY KEY,
    action NVARCHAR(50) NOT NULL,
    target_id NVARCHAR(50) NOT NULL,
    description NVARCHAR(MAX),
    created_at DATETIME DEFAULT GETDATE()
);
GO

-- ============================================================
-- 9. CHEN DU LIEU KHOI TAO (CO TIENG VIET CHUAN N'...')
-- ============================================================

-- Danh sach doan tau
INSERT INTO trains (train_id, train_name, train_type, capacity, max_speed, status) VALUES
('KH1', 'SE1', 'Passenger', 500, 120, 'ACTIVE'),
('KH2', 'SE3', 'Passenger', 450, 120, 'ACTIVE'),
('KH3', 'SE5', 'Passenger', 450, 110, 'ACTIVE'),
('KH4', 'SE7', 'Passenger', 500, 110, 'ACTIVE'),
('KH5', 'SE19', 'Passenger', 400, 100, 'ACTIVE'),
('KH6', 'TN1', 'Passenger', 400, 100, 'ACTIVE'),
('KH7', 'TN3', 'Passenger', 400, 100, 'ACTIVE'),
('KH8', 'SE2', 'Passenger', 500, 120, 'ACTIVE'),
('KH9', 'SE4', 'Passenger', 450, 120, 'ACTIVE'),
('KH10', 'SE6', 'Passenger', 450, 110, 'ACTIVE'),
('KH11', 'SE8', 'Passenger', 500, 110, 'ACTIVE'),
('KH12', 'TN2', 'Passenger', 400, 100, 'ACTIVE'),
('HH1', 'HH01', 'Freight', 800, 90, 'ACTIVE'),
('HH2', 'HH03', 'Freight', 850, 90, 'ACTIVE'),
('HH3', 'HH05', 'Freight', 850, 80, 'ACTIVE');

-- Danh sach nha ga
INSERT INTO stations (station_id, station_name, location, number_of_tracks) VALUES
('HANOI', N'Hà Nội', N'Miền Bắc', 5),
('LAOCAI', N'Lào Cai', N'Miền Bắc', 3),
('HAIPHONG', N'Hải Phòng', N'Miền Bắc', 4),
('THANHHOA', N'Thanh Hóa', N'Miền Trung', 4),
('VINH', N'Vinh', N'Miền Trung', 4),
('DONGHOI', N'Đồng Hới', N'Miền Trung', 3),
('HUE', N'Huế', N'Miền Trung', 3),
('DANANG', N'Đà Nẵng', N'Miền Trung', 5),
('QUYNHON', N'Quy Nhơn', N'Miền Trung', 3),
('KHANHHOA', N'Khánh Hòa', N'Miền Trung', 5),
('DALAT', N'Đà Lạt', N'Tây Nguyên', 2),
('DAKLAK', N'Đắk Lắk', N'Tây Nguyên', 2),
('BINHTHUAN', N'Bình Thuận', N'Miền Trung', 3),
('BIENHOA', N'Biên Hòa', N'Miền Nam', 4),
('SAIGON', N'Sài Gòn', N'Miền Nam', 6);

-- Danh sach tuyen duong noi truc tiep
INSERT INTO routes (route_id, from_station_id, to_station_id, distance, travel_time, status) VALUES
('R01', 'HANOI', 'LAOCAI', 296, 480, 'ACTIVE'),
('R02', 'HANOI', 'HAIPHONG', 102, 150, 'ACTIVE'),
('R03', 'HANOI', 'THANHHOA', 175, 180, 'ACTIVE'),
('R04', 'THANHHOA', 'VINH', 144, 150, 'ACTIVE'),
('R05', 'VINH', 'DONGHOI', 195, 200, 'ACTIVE'),
('R06', 'DONGHOI', 'HUE', 166, 180, 'ACTIVE'),
('R07', 'HUE', 'DANANG', 103, 150, 'ACTIVE'),
('R08', 'DANANG', 'QUYNHON', 305, 300, 'ACTIVE'),
('R09', 'QUYNHON', 'KHANHHOA', 215, 240, 'ACTIVE'),
('R10', 'KHANHHOA', 'BINHTHUAN', 240, 250, 'ACTIVE'),
('R11', 'BINHTHUAN', 'BIENHOA', 140, 150, 'ACTIVE'),
('R12', 'BIENHOA', 'SAIGON', 30, 45, 'ACTIVE'),
('R13', 'KHANHHOA', 'DAKLAK', 190, 240, 'ACTIVE'),
('R14', 'KHANHHOA', 'DALAT', 135, 180, 'ACTIVE');

-- Danh sach lich chay
INSERT INTO schedules (schedule_id, train_id, departure_station_id, destination_station_id, departure_time, arrival_time, priority, status, departure_date) VALUES
('SC01', 'KH1', 'HANOI', 'HAIPHONG', 360, 510, 90, 'SCHEDULED', '30/09/2026'),
('SC02', 'KH2', 'HUE', 'DANANG', 480, 630, 85, 'SCHEDULED', '30/09/2026'),
('SC03', 'KH3', 'DANANG', 'DAKLAK', 420, 1200, 80, 'SCHEDULED', '30/09/2026'),
('SC04', 'HH1', 'HAIPHONG', 'HANOI', 840, 990, 50, 'SCHEDULED', '30/09/2026'),
('SC05', 'KH4', 'HUE', 'DANANG', 510, 660, 75, 'SCHEDULED', '30/09/2026');

-- Danh sach diem dung trung gian
INSERT INTO stops (schedule_id, stop_order, station_id, arrival_time, departure_time) VALUES
('SC02', 1, 'HUE', 480, 480),
('SC02', 2, 'DANANG', 630, 630),
('SC03', 1, 'DANANG', 420, 420),
('SC03', 2, 'QUYNHON', 720, 730),
('SC03', 3, 'KHANHHOA', 970, 980),
('SC03', 4, 'DAKLAK', 1200, 1200),
('SC05', 1, 'HUE', 510, 510),
('SC05', 2, 'DANANG', 660, 660);
GO

-- Kiem tra ket qua
SELECT 'trains' AS TableName, COUNT(*) AS TotalRows FROM trains
UNION ALL
SELECT 'stations', COUNT(*) FROM stations
UNION ALL
SELECT 'routes', COUNT(*) FROM routes
UNION ALL
SELECT 'schedules', COUNT(*) FROM schedules
UNION ALL
SELECT 'stops', COUNT(*) FROM stops;
GO
