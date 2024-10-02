lint:
	pycodestyle . --ignore=E501

publish: clean
	python3 -m build
	ls dist
	twine upload dist/*.tar.gz
	make clean

clean:
	rm -rf .pytest_cache build dist breakout_detection.egg-info
