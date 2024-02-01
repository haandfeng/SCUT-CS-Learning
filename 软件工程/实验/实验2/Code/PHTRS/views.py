from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, Http404, HttpResponseRedirect
from django.urls import reverse
from .models import *
from django.views import generic
from django.template import loader
from django.core.exceptions import ObjectDoesNotExist
from django.contrib.auth.decorators import login_required

def index(request):
    latest_hole_list = Hole.objects.all()
    context = {
        'latest_hole_list': latest_hole_list,
    }
    if request.user.is_authenticated:
        context['user'] = request.user
    return render(request, 'PHTRS/index.html', context)

# @login_required
def detail(request, pk):
    hole = get_object_or_404(Hole, pk=pk)
    context = {
        'hole': hole,
        # 'user': request.user,
    }
    if hasattr(hole, 'state'):
        context['hand_over'] = 'true'
    else:
        context['hand_over'] = 'false'
    return render(request, 'PHTRS/detail.html', context)


#
# class DetailView(generic.DetailView):
#     model = Question
#     template_name = 'PHTRS/detail.html'
#
#
# class ResultsView(generic.DetailView):
#     model = Questiond
#     template_name = 'PHTRS/results.html'
#
# def vote(request, question_id):
#     question = get_object_or_404(Question, pk=question_id)
#     try:
#         selected_choice = question.choice_set.get(pk=request.POST['choice'])
#     except (KeyError, Choice.DoesNotExist):
#         # Redisplay the question voting form.
#         return render(request, 'PHTRS/detail.html', {
#             'question': question,
#             'error_message': "You didn't select a choice.",
#         })
#     else:
#         selected_choice.votes += 1
#         selected_choice.save()
#         # Always return an HttpResponseRedirect after successfully dealing
#         # with POST data. This prevents data from being posted twice if a
#         # user hits the Back button.
#         return HttpResponseRedirect(reverse('PHTRS:results', args=(question.id,)))

from django.http import HttpResponse

