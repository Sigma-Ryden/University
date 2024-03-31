from django.contrib import admin

# Register your models here.

from .models import *

class BookingAdmin(admin.ModelAdmin):
	list_display = ('book_ref', 'book_data', 'total_amount')
	search_fields = ('book_ref', 'book_data', 'total_amount')

class TicketAdmin(admin.ModelAdmin):
	list_display = ('ticket_no', 'passenger_id', 'passenger_name', 'contact_data')
	search_fields = ('ticket_no', 'book_ref', 'passenger_id', 'passenger_name', 'contact_data')


class AirportAdmin(admin.ModelAdmin):
	list_display = ('airport_code', 'airport_name', 'city', 'longitude', 'latitude', 'timezone')
	search_fields = ('airport_code', 'airport_name', 'city', 'longitude', 'latitude', 'timezone')

class AircraftAdmin(admin.ModelAdmin):
	list_display = ('aircraft_code', 'range_of', 'model')
	search_fields = ('aircraft_code', 'range_of', 'model')

class SeatAdmin(admin.ModelAdmin):
	list_display = ('seats_no', 'aircraft_code', 'fare_conditions')
	search_fields = ('seats_no', 'aircraft_code', 'fare_conditions')


class FlightAdmin(admin.ModelAdmin):
	list_display = ('flight_id', 'flight_no', 'scheduled_departure', 'departure_airport', 'arrival_airport', 'actual_departure', 'actual_arrival', 'status')
	search_fields = ('flight_id', 'flight_no', 'aircraft_code', 'airport_code', 'scheduled_departure', 'departure_airport', 'arrival_airport', 'actual_departure', 'actual_arrival', 'status')


class TicketFlightAdmin(admin.ModelAdmin):
	list_display = ('ticket_no', 'fare_conditions', 'amount')
	search_fields = ('ticket_no', 'flight_id', 'fare_conditions', 'amount')


class BoardingPassAdmin(admin.ModelAdmin):
	list_display = ('flight_id', 'boarding_no', 'seat_no')
	search_fields = ('ticket_no', 'flight_id', 'boarding_no', 'seat_no')


admin.site.register(Booking, BookingAdmin)
admin.site.register(Ticket, TicketAdmin)
admin.site.register(Airport, AirportAdmin)
admin.site.register(Aircraft, AircraftAdmin)
admin.site.register(Seat, SeatAdmin)
admin.site.register(Flight, FlightAdmin)
admin.site.register(TicketFlight, TicketFlightAdmin)
admin.site.register(BoardingPass, BoardingPassAdmin)