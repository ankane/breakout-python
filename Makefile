.PHONY: lint build publish clean

lint:
	pycodestyle . --ignore=E501

build:
	python3 -m build

publish: clean build
	twine upload dist/*.tar.gz

clean:
	rm -rf .pytest_cache dist breakout_detection.egg-info
