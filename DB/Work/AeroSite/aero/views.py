from django.shortcuts import render
from django.http import HttpResponse

from django.template import loader

from .models import *

# Create your views here.

def booking_index(request):
    template = loader.get_template("booking/index.html")
    bookings = Booking.objects.order_by("book_ref")
    context = { 'bookings': bookings }

    return HttpResponse(template.render(context, request))

def ticket_index(request):
    template = loader.get_template("ticket/index.html")
    tickets = Ticket.objects.order_by("ticket_no")
    context = { 'tickets': tickets }

    return HttpResponse(template.render(context, request))

def airport_index(request):
    template = loader.get_template("airport/index.html")
    airports = Airport.objects.order_by("airport_code")
    context = { 'airports': airports }

    return HttpResponse(template.render(context, request))

def aircraft_index(request):
    template = loader.get_template("aircraft/index.html")
    aircrafts = Aircraft.objects.order_by("aircraft_code")
    context = { 'aircrafts': aircrafts }

    return HttpResponse(template.render(context, request))

def seat_index(request):
    template = loader.get_template("seat/index.html")
    seats = Seat.objects.order_by("seats_no")
    context = { 'seats': seats }

    return HttpResponse(template.render(context, request))

def flight_index(request):
    template = loader.get_template("flight/index.html")
    flights = Flight.objects.order_by("flight_id")
    context = { 'flights': flights }

    return HttpResponse(template.render(context, request))
    
def ticket_flight_index(request):
    template = loader.get_template("ticket_flight/index.html")
    ticket_flights = TicketFlight.objects.order_by("ticket_no")
    context = { 'ticket_flights': ticket_flights }

    return HttpResponse(template.render(context, request))
    
def boarding_pass_index(request):
    template = loader.get_template("boarding_pass/index.html")
    boarding_passes = BoardingPass.objects.order_by("boarding_no")
    context = { 'boarding_passes': boarding_passes }

    return HttpResponse(template.render(context, request))
