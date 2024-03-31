from django.urls import path

from .views import *

urlpatterns = [
	path('booking/', booking_index),
	path('ticket/', ticket_index),
	path('airport/', airport_index),
	path('aircraft/', aircraft_index),
	path('seat/', seat_index),
	path('flight/', flight_index),
	path('ticketflight/', ticket_flight_index),
	path('boardingpass/', boarding_pass_index),
]