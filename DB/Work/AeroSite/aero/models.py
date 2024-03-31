from django.db import models

# Create your models here.

class Booking(models.Model):
    book_ref = models.CharField(max_length=40, primary_key=True, unique=True, verbose_name='book_ref')
    
    book_data = models.DateTimeField(verbose_name='book_data')
    total_amount = models.DecimalField(max_digits=11, decimal_places=2, verbose_name='total_amount')

    def __str__(self):
        return self.book_ref


class Ticket(models.Model):
    ticket_no = models.IntegerField(primary_key=True, unique=True, verbose_name='ticket_no')
    
    book_ref = models.ForeignKey('Booking', to_field='book_ref', on_delete=models.PROTECT, verbose_name='book_ref')
    
    passenger_id = models.IntegerField(verbose_name='passenger_id')
    passenger_name = models.CharField(max_length=20, verbose_name='passenger_name')
    contact_data = models.CharField(max_length=20, verbose_name='contact_data')

    def __str__(self):
        return self.passenger_name


class Airport(models.Model):
    airport_code = models.IntegerField(primary_key=True, unique=True, verbose_name='airport_code')
    
    airport_name = models.CharField(max_length=30, verbose_name='airport_name')
    city = models.CharField(max_length=30, verbose_name='city')
    
    longitude = models.CharField(max_length=20, verbose_name='longitude')
    latitude = models.CharField(max_length=20, verbose_name='latitude')
    
    timezone = models.DateTimeField(verbose_name='timezone')

    def __str__(self):
        return self.airport_name + " at the (" + self.longitude + ", " + self.latitude + ")"


class Aircraft(models.Model):
    aircraft_code = models.IntegerField(primary_key=True, unique=True, verbose_name='aircraft_code')
    range_of = models.IntegerField(verbose_name='range')
    model = models.CharField(max_length=20, verbose_name='model')

    def __str(self):
        return self.model


class Seat(models.Model):
    seats_no = models.IntegerField(primary_key=True, unique=True, verbose_name='seats_no')
    
    aircraft_code = models.ForeignKey('Aircraft', to_field='aircraft_code', on_delete=models.PROTECT, verbose_name='aircraft_code')
    
    class FareCondition(models.IntegerChoices):
        low = 0
        medium = 1
        hight = 2


    fare_conditions = models.IntegerField(choices=FareCondition.choices, verbose_name='fare_conditions')

    def __str(self):
        return self.aircraft_code + " " + self.seats_no + " " + self.fare_conditions


class Flight(models.Model):
    flight_id = models.IntegerField(primary_key=True, unique=True, verbose_name='flight_id')

    flight_no = models.IntegerField(verbose_name='flight_no')

    aircraft_code = models.ForeignKey('Aircraft', to_field='aircraft_code', on_delete=models.PROTECT, verbose_name='aircraft_code')
    airport_code = models.ForeignKey('Airport', to_field='airport_code', on_delete=models.PROTECT, verbose_name='airport_code')

    scheduled_departure = models.DateTimeField(verbose_name='scheduled_departure')
    departure_airport = models.CharField(max_length=30, verbose_name='departure_airport')

    arrival_airport = models.CharField(max_length=30, verbose_name='arrival_airport')
    actual_departure = models.DateTimeField(verbose_name='actual_departure')
    actual_arrival = models.DateTimeField(verbose_name='actual_arrival')

    status = models.BooleanField(default=False, verbose_name='status')

    def __str(self):
        return self.aircraft_code + " " + self.airport_code + " " +  self.flight_id + " " + self.flight_no


class TicketFlight(models.Model):
    ticket_no = models.ForeignKey('Ticket', to_field='ticket_no', on_delete=models.PROTECT, verbose_name='ticket_no')
    flight_id = models.ForeignKey('Flight', to_field='flight_id', on_delete=models.PROTECT, verbose_name='flight_id')

    class FareCondition(models.IntegerChoices):
        low = 0
        medium = 1
        hight = 2


    fare_conditions = models.IntegerField(choices=FareCondition.choices, verbose_name='fare_conditions')
    amount = models.DecimalField(max_digits=11, decimal_places=2, verbose_name='amount')

    def __str(self):
        return self.ticket_no + " " + self.flight_id + " " + self.fare_conditions + " " + self.amount


class BoardingPass(models.Model):
    ticket_no = models.ForeignKey('Ticket', to_field='ticket_no', on_delete=models.PROTECT, verbose_name='ticket_no')

    flight_id = models.IntegerField(verbose_name='flight_id')

    boarding_no = models.IntegerField(verbose_name='boarding_no')
    seat_no = models.IntegerField(verbose_name='seat_no')

    def __str(self):
        return self.ticket_no + " " + self.boarding_no + " " + self.seat_no

    class Meta:
        verbose_name_plural = "BoardingPasses"
        verbose_name = "BoardingPass"