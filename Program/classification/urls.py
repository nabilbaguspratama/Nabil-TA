from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('result', views.classify, name='classify'),
    path('home', views.home, name='home')
]