from django.shortcuts import render
from django.http import HttpResponse
from api.response import Response
from . import transformer
from .models import Muscles
import pandas as pd
from . import main

def index(request):
    return Response.ok({"response": 200})

def classify(request):
    muscles = Muscles.objects.all()
    muscles = transformer.transform(muscles)
    result = main.classify(muscles, request)
    return render(request, 'result.html', {
        'train_score': round(result['0']['train_score'] * 100,2),
        'test_score': round(result['0']['test_score'] * 100,2),
        'train_time': result['0']['train_time']
    })

def home(request):
    return render(request, 'main.html', {})