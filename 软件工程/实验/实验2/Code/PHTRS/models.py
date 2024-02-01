import datetime
from django.db import models
from django.utils import timezone
from django.core.validators import MaxValueValidator, MinValueValidator, RegexValidator


# Create your models here.


class Hole(models.Model):

    def __str__(self):
        return self.district + ' ' + self.street

    def getPriority(self):
        return int(10 - self.hole_size / 2)

    def was_published_recently(self):
        return self.submit_date >= timezone.now() - datetime.timedelta(days=1)

    reporter = models.CharField('Reporter Name', max_length=100)
    district = models.CharField(max_length=200)
    street = models.CharField(max_length=200)
    hole_size = models.IntegerField('Size of the hole (1-10)',
                                    validators=[
                                        MaxValueValidator(10),
                                        MinValueValidator(1)
                                    ])
    hole_location = models.CharField('Location of the hole', max_length=20)

    submit_date = models.DateTimeField('Submit Date', default=timezone.now())


class State(models.Model):
    hole = models.OneToOneField(
        Hole,
        on_delete=models.CASCADE,
        primary_key=True,
    )

    def __str__(self):
        return str(self.hole)

    isFixed = models.BooleanField(default=False)
    crews = models.CharField(max_length=200)
    hole_status = models.CharField(max_length=50,
                                   validators=[
                                       RegexValidator("^repairing$|^repaired$|^temporaryRepaired$|^notRepaired$",
                                                      message='status invalid！')],
                                   default='notRepaired')
    equipment = models.CharField(max_length=200)
