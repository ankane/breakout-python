lint:
	pycodestyle . --ignore=E501

publish: clean
	python3 setup.py sdist
	ls dist
	# twine upload dist/*
	make clean

clean:
	rm -rf .pytest_cache build dist breakout_detection.egg-info
