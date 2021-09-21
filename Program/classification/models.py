from django.db import models

class Muscles(models.Model):
    id = models.BigAutoField(primary_key=True)
    min = models.DecimalField(max_digits=5, decimal_places=2)
    max = models.DecimalField(max_digits=5, decimal_places=2)
    mean = models.DecimalField(max_digits=5, decimal_places=2)
    stdev = models.DecimalField(max_digits=5, decimal_places=2)
    median = models.DecimalField(max_digits=5, decimal_places=2)
    variance = models.DecimalField(max_digits=5, decimal_places=2)
    label = models.BigIntegerField()

    class Meta:
        db_table = 'muscles'