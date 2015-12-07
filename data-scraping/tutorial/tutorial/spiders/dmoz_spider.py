from scrapy.spider import BaseSpider

from tutorial.items import DmozItem

class DmozSpider(BaseSpider):
    name = 'dmoz'
    allowed_domains = ['dmoz.org']
    start_urls = [
        'http://dmoz.org/Computers/Programming/Languages/Python/Books/',
        'http://dmoz.org/Computers/Programming/Languages/Python/Resources/'
    ]

    def parse(self, response):
       filename = response.url.split('/')[-2] + '.html'
       for sel in response.xpath('//ul/li'):
           #title = sel.xpath('a/text()').extract()
           #link = sel.xpath('a/@href').extract()
           #desc = sel.xpath('text()').extract()
           #print title, link, desc
           #f.write(title, link, desc)

            item = DmozItem()
            item['title'] = sel.xpath('a/text()').extract()
            item['link'] = sel.xpath('a/@href').extract()
            item['desc'] = sel.xpath('text()').extract()
            return(item)
