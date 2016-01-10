# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

from scrapy.item import Item, Field

class TorrentItem(Item):
    url = Field()
    name = Field()
    description = Field()
    size = Field()

class MininovaSpider(CrawlSpider):

    name = 'mininova'
    allowed_domains = ['mininova.org']
    start_urls = ['http://www.mininova.org/today']
    rules = [Rule(SgmlLinkExtractor(allow=['/tor/\d+']), 'parse_torrent')]

    def parse_torrent(self, response):
        sel = Selector(response)
        torrent = TorrentItem()
        torrent['url'] = response.url
        torrent['name'] = sel.xpath("//h1/text()").extract()
        torrent['description'] = sel.xpath("//div[@id='description']").extract()
        torrent['size'] = sel.xpath("//div[@id='info-left']/p[2]/text()[2]").extract()
        return torrent

class MininovaPipeline(object):
    def process_item(self, item, spider):
        return item
